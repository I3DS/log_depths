#include <i3ds/configurator.hpp>
#include <i3ds/subscriber.hpp>
#include <i3ds/tof_camera_sensor.hpp>
#include <i3ds/frame.hpp>
#include <i3ds/depthmap.hpp>

#include <csignal>
#include <iostream>
#include <fstream>

std::atomic<bool> running;
std::mutex mtx;
unsigned int captured;
std::ofstream logfile;

void signal_handler(int)
{
    running = false;
}

void update_captured(const unsigned int &n_measurements) {
  captured++;
  if (n_measurements != 0 && captured >= n_measurements) {
    running = false;
  }
}

void write_center_value(i3ds::DepthMap &dm, const unsigned int n_measurements) {
  float center_value =
      dm.depths[(dm.descriptor.width / 2) * (dm.descriptor.height + 1)];
  std::cout << center_value << "\n";
  {
    std::lock_guard<std::mutex> guard(mtx);
    logfile << center_value << "\n";
    update_captured(n_measurements);
  }
}

void write_whole_dm(i3ds::DepthMap &dm, const unsigned int n_measurements)
{
    {
        std::lock_guard<std::mutex> guard(mtx);
        std::cout << "Got " << dm.depths.size() << "floats\n";
        for (int i = 0; i < dm.depths.size(); ++i)
        {
            logfile << dm.depths[i] <<';';
        }
        logfile << '\n';
        update_captured(n_measurements);
    }
}


int main(int argc, char *argv[])
{
    running = true;
    captured = 0;
    int node;
    unsigned int n_measurements;
    bool whole_dm;
    std::string outfilename;
    i3ds::Configurator configurator;
    po::options_description desc("Captures ToF depthmaps and logs the center value to file\n  Available options");
    configurator.add_common_options(desc);
    desc.add_options()
        ("node,n", po::value<int>(&node)->default_value(10), "Node ID of camera")
        ("measurements,m", po::value<unsigned int>(&n_measurements)->default_value(0), "Number of measurements to capture (0 means no limit)")
        ("output,o", po::value(&outfilename)->default_value("tof.log"), "Output file")
        ("whole_dm,w", po::bool_switch(&whole_dm)->default_value(false), "Log whole depth map to file")
        ;
    po::variables_map vm = configurator.parse_common_options(desc, argc, argv);

    std::cout << "Connecting to Node with ID: " << node << std::endl;
    i3ds::Context::Ptr context = i3ds::Context::Create();
    i3ds::Subscriber subscriber(context);

    if (whole_dm) {
        logfile.open(outfilename, std::ofstream::out | std::ofstream::binary);
        subscriber.Attach<i3ds::ToFCamera::MeasurementTopic>(node, [n_measurements](auto d){write_whole_dm(d, n_measurements);});
    }
    else {
        logfile.open(outfilename, std::ofstream::out);
        subscriber.Attach<i3ds::ToFCamera::MeasurementTopic>(node, [n_measurements](auto d){write_center_value(d, n_measurements);});
    }

    subscriber.Start();

    signal(SIGINT, signal_handler);

    while(running)
    {
        sleep(1);
    }
    subscriber.Stop();
    logfile.close();
    std::cout << "Captured " << captured << " measurements\n";

    return 0;
}

# Experiments description
The experiments were done in two different setups: the office and the cellar.

The office has the following potential 
* **Motion Capture system on standby**. Motion capture uses IR signals, and this could potentially disturb the experiment, even on standby mode.
* **Light**. There were light coming from ceiling lamps.
* **Reflective surfaces**. There are glass walls in the office space.

The cellar had none of these issues. In the cellar we did several experiments with and without light, with computer or outlet power, and with a single or two cameras running at the same time.

The main setups for the experiments:
| Experiment setup | Distance [cm] | Range mode | 
|------------|---------------|------------|
| 1          | 35            | 0          | 
| 2          | 40            | 0          | 
| 3          | 100           | 0          | 
| 4          | 100           | 2          | 
| 5          | 200           | 2          | 
| 6          | 200           | 5          | 
| 7          | 300           | 2          | 
| 8          | 300           | 5          | 
| 9          | 400           | 2          | 
| 10         | 400           | 5          | 
| 11         | 500           | 5          | 
| 12         | 600           | 5          | 
| 13         | 620           | 5          | 

In addition, experiments in the cellar did several extra tests for each to test additional factors:
- Setup 8-11 were done with both light (ceiling lamps) and darkness
- Setup 9-13 were done with one camera using power from the computer, and one camera using 5.5V from the wall outlet.
- Setup 10-11 were done with cameras running alone or both at the same time
- Setup 10 were done with different FPS
- Setup 10 were done with both hot and cold cameras

To measure the distance from the camera to the object, we used a laser distance measurer from Bosch. each experiment was setup with a distance from the front of the camera to the object.

## Log files naming
The results from the experiments were logged in .log files. They have the following conventions:
- They start with the experiment setup number (exp1, ...) corresponding to the distance and range mode used
- The second term is the serial number of the camera, which for these cameras ended with 788 and 800.
- The third term says if the test was done in darkness or with ceiling lamps on (light)
- the fourth says if the camera was running alone (one at a time), or if both cameras were running at the same time
- If the camera was powered with 5.5V from the wall outlet, it has "power" in the filename, otherwise it was powered from the computer
- One log (exp10) has the "cold" name at the end, this means that the camera was just turned on and not warm. On the other tests, the camera could be up to 48 degree celcius.
- Lastly, all experiments were done using high FPS (40 000ms period / ~25fps), but exp10 setup was also tried with low fps, and this is signified at the end of the log name with "lowfps".
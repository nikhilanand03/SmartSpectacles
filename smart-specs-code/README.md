## mictest.ino

- This takes analog input from the microphone and prints the values continuously. Those values represent the y-values of the sound wave. 
- So, on the Serial plotter, in a quiet environment, we see a perfect sine wave. And on increasing frequency, the waves frequency increases visibly. 
- But every time we talk, there is a sudden disturbance. And general talking noise around produces a disturbance of high amplitude. 
- But overall, we can filter out really high frequencies representing noise, and ignore low amplitudes. Apart from that, everything should be visible on the LEDs.

Thus, our microphone works and produces data. We can now collect data points from 4 microphones in an array and feed it into the algorithm.

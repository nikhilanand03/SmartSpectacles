## mictest.ino

- This takes analog input from the microphone and prints the values continuously. Those values represent the y-values of the sound wave. 
- So, on the Serial plotter, in a quiet environment, we see a perfect sine wave. And on increasing frequency, the waves frequency increases visibly. 
- But every time we talk, there is a sudden disturbance. And general talking noise around produces a disturbance of high amplitude. 
- But overall, we can filter out really high frequencies representing noise, and ignore low amplitudes. Apart from that, everything should be visible on the LEDs.

*Inference*: Thus, our microphone works and produces data. We can now collect data points from 4 microphones in an array and feed it into the algorithm.

## FFTTest.ino

- Here we take samples of the analog input from the microphone once every 0.001 seconds, over 64 iterations (64 samples). This data is then used to divide it into frequencies and prints out the magnitude of each of the frequencies. The frequencies of the highest magnitudes will probably be the most prominent ones (which we would need to find the directions of). 
- So that should be kept in mind while making the algorithm. 
- Anyway, in this demo, we simply print out the magnitudes of each of the frequencies and print out the frequency of maximum magnitude. 
- We need to keep the sample frequency as double the maximum frequency that can be detected. So, if sample frequency = 1000, then a maximum frequency of 500 can be detected.
- We then play around with various frequencies on the frequency generator and see if the program is able to detect the frequency.

*Inference*: The FFT works on the data we have and we can split it into different frequencies at different magnitudes.

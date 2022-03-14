## mictest.ino

- This takes analog input from the microphone and prints the values continuously. Those values represent the y-values of the sound wave. 
- So, on the Serial plotter, in a quiet environment, we see a perfect sine wave. And on increasing frequency, the waves frequency increases visibly. 
- But every time we talk, there is a sudden disturbance. And general talking noise around produces a disturbance of high amplitude. 
- But overall, we can filter out really high frequencies representing noise, and ignore low amplitudes. Apart from that, everything should be visible on the LEDs.

### Lowest frequency
<img width="674" alt="level1" src="https://user-images.githubusercontent.com/75153414/154753954-0ad557de-4c3b-440a-b30d-c9195623b9e0.png">

### Middle frequency
<img width="784" alt="level2" src="https://user-images.githubusercontent.com/75153414/154753977-6a3eeb64-0386-42c3-97e6-2e11142f9cd4.png">

### Highest frequency
<img width="745" alt="level3" src="https://user-images.githubusercontent.com/75153414/154754027-7a14f9ec-70b6-4a6a-88ad-e48bbcdef657.png">


*Inference*: Thus, our microphone works and produces data. We can now collect data points from 4 microphones in an array and feed it into the algorithm.

## FFTTest.ino

- Here we take samples of the analog input from the microphone once every 0.001 seconds, over 64 iterations (64 samples). This data is then used to divide it into frequencies and prints out the magnitude of each of the frequencies. The frequencies of the highest magnitudes will probably be the most prominent ones (which we would need to find the directions of). 
- So that should be kept in mind while making the algorithm. 
- Anyway, in this demo, we simply print out the magnitudes of each of the frequencies and print out the frequency of maximum magnitude. 
- We need to keep the sample frequency as double the maximum frequency that can be detected. So, if sample frequency = 1000, then a maximum frequency of 500 can be detected.
- We then play around with various frequencies on the frequency generator and see if the program is able to detect the frequency.

### Sound with maximum frequency of 366
<img width="167" alt="pic1" src="https://user-images.githubusercontent.com/75153414/154754520-ce0c101a-c19c-4f21-bac5-c6fdb63846dc.png">

### Sound with maximum frequency of 201
<img width="171" alt="pic2" src="https://user-images.githubusercontent.com/75153414/154754528-0944464f-3be3-4358-af94-a96f2462e6c3.png">

*Inference*: The FFT works on the data we have and we can split it into different frequencies at different magnitudes.

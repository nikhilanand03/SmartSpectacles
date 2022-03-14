# Open House Prototype

For our final prototype for the Open House, we used Analog microphones (due to inavailability of Digital ones), and utilised Parseval's theorem to calculate which
microphone is receiving more power, and determing the direction of left or right based on that.

The 'analog2mics.ino' file is for testing the 2 microphones. This code was then integrated into the Wifi Access Point code, to get the second file
'WifiAccessPoint.ino'. Thus, it is able to continuously collect audio data from the two microphones, and run a web server at the specific addresses simultaneously.

Now, the Python code keeps reading the Serial Monitor and takes the last 500 data points printed to it by the 'WifiAccessPoint.ino' code. Then, it passes these
data points through the algorithm based on Parseval's Theorem, to finally calculate which microphone is receiving more power and then opens a web server link in
order to get the corresponding LED to light up.

Thus this completes the prototype.

<img width="665" alt="image" src="https://user-images.githubusercontent.com/75153414/158164254-bf56aa26-3069-4bb3-bca0-257f5f50ee55.png">

## Open House Presentation


[SMART SPECTACLES.pdf](https://github.com/nikhilanand03/SmartSpectacles/files/8244353/SMART.SPECTACLES.pdf)

# Smart Spectacles
This repository contains some of the code that was made for our Smart Spectacles project done as a project under CFI Electronics Club in the year 2021-22. An extract on the idea behind the project is detailed below.

## Problem Statement
Essentially, deaf people face difficulties in the world, and this project aims to fix that (at least certain aspects of it). There are a lot of instances where we need to be ‘alerted’ by certain sounds, and this product is meant to give the deaf as well as those who are hard of hearing an opportunity to be alerted by such sounds as well.

*Note:* In my analysis, I will focus more on the first stage, i.e, developing a working prototype that detects directional and intensity-related aspects of sound and displays these.

## Approach to solve the problem
In this project, the team will create a certain arrangement of lights that will turn on when sounds are heard by the device, and it may light up in a particular way depending on the direction of the sound source.

A proof of concept has already been developed for this project. The next step that needs to be carried out is to figure out an appropriate algorithm to find the direction of sound waves using a phased array system of 4 microphones. We use structures like Fast Fourier Transform to find the frequency components of the sound, and eliminate higher frequencies that are a part of the 'noise'. Finally, we can analyse the sound direction and print out an angle based on it. This will determine the way the LEDs on the glasses will light up.

## General Steps
- The first step is 'mictest.ino'. Here, we test the input of the Analog microphones.
- The next step is 'FFTTest.ino'. Here we take samples of Analog input and perform an FFT to find the most prominent frequency of sound (see if this aspect is working right).
- Now after this, we use a combination of FFTs and an algorithm that uses a phased array of microphones and inputs the analog input of all 4 microphones for a given sound source, as well as the exact arrangement of microphones, and outputs the direction (theta) of the sound source.

## Prototyping and testing
The designing of the product is happening simultaneously. We need to 3D print our design, and insert the microphones and LEDs appropriately. So that we can properly load our code and test it for various inputs. But we can't test our product without all 4 microphones. 

We’ll need to create an appropriate microphone array that can properly identify the magnitude and direction of sounds (some more on this has been explained in a research paper whose link was added on the CFI discourse portal). Also the system of LEDs should be added.

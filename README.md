# Embedded Programming projects

This repository aims to integrate all my projects done related to embedded programming.

## [Wireway](wireway)

This was developed as part of my final course project to graduate as a B.Sc. in Information Technology.
The general idea of the project was to enable developers without much knowledge on embedded-systems to program
their Arduino boards through an online Web-editor using a high-level JavaScript API. 

In principle, you would buy a pre-programmed board with the capability to receive commands from a WebServer.
Once logged on this WebServer you can scan and register your brand new board and start programming it.
The programming was abstract with a high-level API in JavaScript capable of talking to your board through the pre-installed firmware.
The image below shows an example of a web-programmed board.

<img alt="Online programmed board" height="500" src="wireway/resources/online-programmed-board.png" width="500"/>

Given the code for your board is ready and uploaded to your Arduino board, after that you could open up your boards dashboards
and actuate controllers by sending signals from the WebApp and reading values from sensors shown on the screen.
The image below shows an example of the previously programmed board being controlled.

<img alt="Online Board control panel" height="500" src="wireway/resources/online-board-control-panel.png" width="500"/>

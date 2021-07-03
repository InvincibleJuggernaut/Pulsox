<p align="center">
  <img src="Assets/logo.bmp">
  </p>
<h2>Introduction</h2>

<p> Pulse oximeters are electronic devices capable of measuring blood oxygen concentration levels as well as heart beat rate. Although they originally found their use only in medical institutions, the COVID-19 pandemic led to rise in demand for such devices. Naturally, prices shot up through the roof with people being forced to buy them at 3-4x the prices to save their dear ones' lives. </p>
<p> Pulsox is an IoT based pulse oximeter capable of detecting heart rate as well as oxygen concentration. The data is displayed locally in the LCD display as well as sent to the Blynk IoT platform. This data can be visualized in real-time through an app. 
  </p>
  
  
<p align="center"><img src="Assets/Test run B.png"></p>
  
<h2>Components</h2>


<ul>
  <li>NodeMCU ESP8266</li>
  <li>MAX30102</li>
  <li>LCD 16x2</li>
  </ul>
  
<h2>Schematic</h2>

<p align="center">
<img src="Assets/Schematic.png">
</p>
<p align="center">
  <b>Circuit schematic</b>
  </p>
  
  <br>
  <br>
  
<h2>Layout</h2>

<p align="center">
<img src="Assets/PCB_A.JPG">
  </p>
  <p align="center">
  <b>PCB layout for Pulsox</b>
</p>

<br>
<br>

<p align="center">
<img src="Assets/PCB_B.png" length="1200" width="800"></p>
<p align="center">
  <b>Real life rendering of PCB</b>
  </p>
  
  <br>
  <br>
  
<p><b>Note:</b> <i> Although the final circuit made use of MAX30102 as the pulse oximetry unit, the PCB design has been made using another pulse oximentry unit called as MAX30100 since there were no footprint libraries available for MAX30102. However, both the sensors are built by Maxim Integrated having similar functions and may only differ in physical dimensions.</i></p>

<h2>License</h2>

<a href="LICENSE">GPLv3</a>

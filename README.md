# Simple-test-rig-for-labview-based-avionics-systems-with-pressure-and-gyro-sensor
1)This is testrig interface
![testrig](https://user-images.githubusercontent.com/83868162/212466844-f38b20c7-469a-4050-8273-f09f314605d5.png)
2)This is part of the block diagram of the project
![image](https://user-images.githubusercontent.com/83868162/212466863-7c5fca6a-ff8e-4c94-9bbf-98c753e4df0a.png)
3)In this section, the user is asked to enter the serial port to which the device is connected, thanks to VISA. With Read, the data in the processor is retrieved from the labview. The command created in the labview environment with Write is transmitted to the processor.
![image](https://user-images.githubusercontent.com/83868162/212466981-8c8e73f2-240e-4b0d-b269-1562d0b3ef8f.png)
4)In this section, the data coming from the processor is visualized. Since these data are taken in string format, they are first divided into subsections according to the index number with the String Subset Function, then converted into decimal number format with the Fract/Exp String To Number Function and made ready for visualization and processing.
![image](https://user-images.githubusercontent.com/83868162/212466987-4d178825-dd49-475c-a41d-19441029eb49.png)
5)In this section, X pain data and Altitude data are put into a condition with In Range and Coerce Function. Accordingly, if the values are between the specified limits, the value of 1 is sent using the Select Function, otherwise the value of 0 is sent. But since VISA is in string format, the values are first converted to string with the help of Number To Decimal String Function and then connected to the write buffer pin of VISA. In this way, the LED in the hardware lights up according to the values.
![image](https://user-images.githubusercontent.com/83868162/212467015-2b76ed21-c393-402f-ab1f-c7d385966398.png)
6)Here, the filing process has been done. Data from VISA READ can be stored on the computer thanks to the Write to Text File Function.
![image](https://user-images.githubusercontent.com/83868162/212467052-0e07d473-7c19-4d0c-9098-22dccb03c00f.png)

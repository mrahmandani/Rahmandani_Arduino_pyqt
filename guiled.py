import sys, os, glob
from PyQt4 import QtCore, QtGui, uic
import serial
import time

qtCreatorFile = "guiled.ui"
Ui_MainWindow, QtBaseClass = uic.loadUiType(qtCreatorFile)

class MyApp(QtGui.QMainWindow, Ui_MainWindow):
	def __init__(self):
		QtGui.QMainWindow.__init__(self)
		Ui_MainWindow.__init__(self)
		self.setupUi(self)
		self.pushButton_OpenSerial.clicked.connect(self.OpenSerial)
		self.pushButton_running.clicked.connect(self.Running)
		self.pushButton_blink.clicked.connect(self.Blink)
		self.pushButton_Exit.clicked.connect(self.AppExit)
		self.textEdit_LogMessage.append("Led menggunakan PyQt - Arduino Uno")
		
	def OpenSerial(self):
		if self.pushButton_OpenSerial.text()=='PLAY':
			self.ser = serial.Serial("COM21", "9600", timeout=0.1)
			if self.ser.isOpen():
				self.pushButton_OpenSerial.setText('STOP')
				self.textEdit_LogMessage.append("OK")
			else:
				self.textEdit_LogMessage.append("Can not Play")
		else:
			if self.ser.isOpen():
				self.ser.close()
			self.pushButton_OpenSerial.setText('PLAY')
			self.textEdit_LogMessage.append("STOP")
			
	def Running (self):
		self.ser.write('A'.encode())
		tON  = self.spinBox_tON.value()
		self.textEdit_LogMessage.append("Sending tON = %d ms" %(tON*100))
		self.TXdata = bytearray(2)
		self.TXdata[0]=tON
		self.ser.write(self.TXdata)
		time.sleep(2)
		self.bytesToRead = self.ser.inWaiting()
		if (self.bytesToRead > 0):
			rxdata = self.ser.read(self.bytesToRead)
			self.textEdit_LogMessage.append(rxdata)
		
	def Blink (self):
		self.ser.write('B'.encode())
		tON  = self.spinBox_tON.value()
		self.textEdit_LogMessage.append("Sending tON = %d ms" %(tON*100))
		self.TXdata = bytearray(2)
		self.TXdata[0]=tON
		self.ser.write(self.TXdata)
		time.sleep(2)
		self.bytesToRead = self.ser.inWaiting()
		if (self.bytesToRead > 0):
			rxdata = self.ser.read(self.bytesToRead)
			self.textEdit_LogMessage.append(rxdata)
				
	def AppExit(self):
		self.textEdit_LogMessage.setText("Exit application")
		sys.exit()


if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    window = MyApp()
    window.show()
    sys.exit(app.exec_())

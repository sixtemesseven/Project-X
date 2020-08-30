# -*- coding: utf-8 -*-
"""
Created on Wed Mar 11 10:32:16 2020

@author: justRandom
"""

from pywinauto.application import Application
from pywinauto import keyboard
import time

#Open ShadoCam and Wait
app = Application()
app.start(r"C:\Program Files (x86)\Rad-icon Imaging\ShadoCam 4.0\ShadoCam.exe")
time.sleep(10)
mainwin = app.window(title_re = u'ShadoCam - Image1')

mainwin.menu_select("Acquisition->Single Image")
time.sleep(2)

#Save image to l

keyboard.send_keys('^s')
keyboard.send_keys('{DEL}')
keyboard.send_keys('testfrompywin.tif')
keyboard.send_keys('{ENTER}')

'''
keyboard.send_keys('^s')
app.SaveAs.EncodingComboBox.select("UTF-8")
app.SaveAs.Edit.set_edit_text("testImagePA.tif")
app.SaveAs.Save.click(double=True)
'''




import time
from switchx7 import SwitchX7 

switch = SwitchX7(port='/dev/ttyACM0',timeout=1.0)

for i in range(0,7):

    switch.set(i,True)
    time.sleep(0.25)

    switch.set(i,False)
    time.sleep(0.25)

switch.set_all(True)
time.sleep(0.25)
switch.set_all(False)


import serial

class SwitchX7(serial.Serial):

    def __init__(self,**kwargs):
        super(SwitchX7,self).__init__(**kwargs)

    def set(self, num, val):
        """
        Set value of individual switches.
        num = swtich number, integer in range (0,1,2,...,6)
        val = switch state, boolean (True/False)
        """
        if not num in range(0,7):
            raise ValueError('num must be between 0 and 7')
        if not type(val) == bool:
            raise  ValueError('val must be boolean')
        if val == True:
            cmd = '[{}, 1]\n'.format(num)
        else:
            cmd = '[{}, 0]\n'.format(num)
        self.write(cmd.encode())

    def set_all(self,val):
        """
        Set state of all switches.
        val = state, boolean (True/False)
        """
        if not type(val) == bool:
            raise ValueError('val must be boolean')
        if val == True:
            cmd = '[7, 1]\n'
        else:
            cmd = '[7, 0]\n'
        self.write(cmd.encode())



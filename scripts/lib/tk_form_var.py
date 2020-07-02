#
# Author: sascha_lammers@gmx.de
#

import tkinter

#
# creates a dictionary from one or more dictionaries that returns
# String(Int/Double/Boolear)Var for the use form widgets. the data is
# synchronized between the dictionaries and widgets automatically
#
# customer = { 'first': 'John', 'last': 'Doe' }
# details = { 'newsletter': False, 'deleted': False }
# data = TkFormVar(customer, details)
#
# tk.Entry(self, textvariable=data['first'])
# tk.Entry(self, textvariable=data['last'])
# tk.Checkbutton(self, variable=data['newsletter'])
# tk.Checkbutton(self, variable=data['deleted'])

class TkFormVar(object):
    def __init__(self, *dicts):
        self._dicts = dicts
        self._tkVars = {}

    def __getitem__(self, key):
        if key in self._tkVars:
            return self._tkVars[key]
        value = self.__dicts_get_item(key)
        if value==None:
            raise KeyError('key does not exist: %s' % key)

        if isinstance(value, int):
            var = tkinter.IntVar()
        elif isinstance(value, bool):
            var = tkinter.BooleanVar()
        elif isinstance(value, float):
            var = tkinter.DoubleVar()
        elif isinstance(value, str):
            var = tkinter.StringVar()
        else:
            raise TypeError('type not supported: %s' % type(value))

        for num, _dict in enumerate(self._dicts):
            if key in _dict:
                var.trace('r', callback=lambda *args,value=_dict[key],var=var: var.set(value))
                var.trace('w', callback=lambda *args,num=num,key=key,var=var: self.__dicts_update(num, key, var))
                var.trace('u', callback=lambda *args,num=num,key=key,var=var: self.__dicts_update(num, key, None))
        self._tkVars[key] = var
        return var

    def __dicts_update(self, num, key, var):
        if var==None:
            del self._dicts[num][key]
        else:
            self._dicts[num][key] = var.get()

    def __dicts_get_item(self, key):
        for _dict in self._dicts:
            if key in _dict:
                return _dict[key]
        return None

    def __contains__(self, key):
        return self.__dicts_get_item(key) != None

    def __len__(self):
        return len(self._tkVars)

    def __repr__(self):
        return repr(self._tkVars)

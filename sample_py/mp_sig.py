'''
Author: avert-win
Date: 2022-07-08 11:37:07
LastEditTime: 2022-07-09 22:30:57
FilePath: \ProgramDaily\sample_py\mp_sig.py
Description: Python多进程类继承、进程回收、信号捕捉及处理、进程退出等。
LastEditors: avert-win
'''
# python doc about signal: https://docs.python.org/3/library/signal.html

'''exit/quit
1. os._exit() 
    Exits without calling any cleanup handlers, only used in child process.
    The function deallocate memory and resources but remain the process's entyr in the process table.
    If the number is not very big, what remain in process table doesn't matter.
2. quit() 
    This should not be used in production code(it can only be used in interpreter.)
    It should be used in imported module.
3. exit() 
    Just like a synonym of quit(), it's defined in site.py.
4. sys.exit([arg]) 
    This is considered good to be used in production code. arg can be an integer  or sth else.
    It's the standard way for any normal process to exit.
'''

'''signal
The default action for SIGINT, SIGTERM, SIGQUIT, SIGKILL is to terminate the process.
1. SIGINT
    It's defined as an interruption requested by the user, so we 
    shouldn't depend on SIGINT to finish a process(unless you write it).
2. SIGQUIT
    It terminate the process and generates a core dump, which is useful for debugging.
3. SIGTERM
    Usually use this signal to terminate the child processes.
4. SIGKILL
    Kill the process. Cause all three signals above can have action override by
    process, SIGKILL is the last way to terminate the process. 
    Also, when a process is hung, it may not respond to any of the three signals,
    in that case, SIGKILL is the only way.
'''

import multiprocessing as mp
from typing import Callable, Iterable, Mapping, Any
import signal
import time
import subprocess as sp

class worker(mp.Process):

    def __init__(self, name: str=None, args=[], daemon: bool = True) -> None:
        '''
        For a class inherited multiprocessing.Process, you needn't target.
        '''
        super().__init__(name=name, args=args, daemon=daemon)
    
    def __SIGINT_handler(self, signum, frame):
        '''
        For a signal handler, you must define it with two arguments: signum and frame.
        Without this handler, <ctrl+c> will turn into an exception of KeyboardInterrupt.
        '''
        print(f'process {self.name} recieved a SIGINT')
        print(f'signum: {signum}')
        exit()

    def __SIGTEM_handler(self, signum, frame):
        print(f'process {self.name} recieved a SIGINT')
        print(f'signum: {signum}')
        exit()
        pass

    def run(self) -> None:
        signal.signal(signal.SIGINT, self.__SIGINT_handler)
        signal.signal(signal.SIGTERM, self.__SIGTEM_handler)
        print('I am ', self.name)
        while True:
            pass
        return super().run()

def SIGINT_handler(signum, frame):
    active = mp.active_children()
    for child in active:
        child.kill()


if __name__ == '__main__':

    signal.signal(signal.SIGINT, SIGINT_handler)

    # subprocess: run command and wait for completion.
    sp.call(['tree'], shell=True)
    # check_call: run command, wait for completion, and return or 
    # raise a CalledProcessError(when errno is not zero).
    sp.check_call(['ls'], shell=True)

    workers = [worker() for i in range(10)]
    for one in workers:
        one.start()
    for one in workers:
        one.join()
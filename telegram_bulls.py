#!/usr/bin/python
from subprocess import Popen, PIPE
import os
from pytg.sender import Sender
from pytg.receiver import Receiver
from pytg import Telegram
from pytg.utils import coroutine
@coroutine
def get_msg():
    while True:
        msg = (yield)
        if (msg.event != 'message'): continue
        if (msg.sender.username != "bulls_n_cows_bot"): continue
        txt = msg.text
        if ('т' in txt):
            break
        txt = txt.split('\n')[-1]
        bulls = '0'
        cows = '0'
        if ('Б' in txt) :
            bulls = txt[8]
        if ('К' in txt) :
            if (bulls != '0'):
                cows = txt[11]
            else:
                cows = txt[8]
        proc.stdin.write(str.encode(bulls + ' ' + cows + '\n'))
        proc.stdin.flush()
        sender.send_msg("@bulls_n_cows_bot", proc.stdout.readline().decode())
        print(txt, bulls, cows)
        #exit(0)
started = (input("Telegram-cli is running? Yes No\n") == "Yes")
if not started:
    telegram = Telegram(telegram = "/usr/bin/telegram-cli", pubkey_file = "/etc/telegram-cli/server.pub")
    sender = telegram.sender
else:
    sender = Sender(host="localhost", port=4458)
num = int(input("Number of games: "))
for i in range(num):
    proc = Popen(["./bulls"], stdout = PIPE, stdin = PIPE)
    ans = proc.stdout.readline()
    sender.send_msg("@bulls_n_cows_bot", ans.decode())
    if not started:
        receiver = telegram.receiver
    else:
        receiver = Receiver(host="localhost", port=4458)
    receiver.start()
    receiver.message(get_msg())
    receiver.stop()

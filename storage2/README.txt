Beginning of cache exercises. It's possible that some of the performance
differences illustrated here will not be apparent in the appliance, so
you may need/want to run them directly on your laptop/desktop. They are
relatively simple programs that should translate easily.

w01 (super slow) O_WRONLY | O_CREAT | O_TRUNC | O_SYNC (1 byte/write)
w02 (quick) O_WRONLY | O_CREAT | O_TRUNC (1 byte/write)
w03 (super quick) stdio (1 byte/write)


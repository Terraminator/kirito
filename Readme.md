<h1> This is a rootkit for playing king of the hill on tryhackme </h1>

This rootkit is based on this tutorial:
<h1> https://h0mbre.github.io/Learn-C-By-Creating-A-Rootkit/# </h1>

Compile and insert the rootkit by running:
<pre> bash make.sh </pre>
(Remember you need to change the port and ip address in the script)

<h1> Get a reverse shell with: </h1>
<pre> touch __UNO & ls & rm __UNO </pre>

hide files:
<pre> everything beginning wit "kir" gets hidden </pre>

The files:
<pre>
/root/king.txt
/etc/ld.so.preload
/lib/libc.kir.so.6
</pre>
will be hidden in the future
<h1> This is a rootkit for playing king of the hill on tryhackme </h1>

DO ONLY USE THIS IN PRIVATE GAMES BECAUSE IT IS GAME BREAKING

This rootkit is based on this tutorial:
<h1> https://h0mbre.github.io/Learn-C-By-Creating-A-Rootkit/# </h1>

Compile and insert the rootkit by running:
<pre> bash make.sh </pre>
you maybe need to change /lib/ to something like /lib/x86_64-linux-gnu/ this is specific for the distribution
(Remember you need to change the port and ip address in the script)

<h1> Get a reverse shell with: </h1>
<pre> touch __UNO & ls & rm __UNO </pre>

hide files:
<pre> everything beginning wit "kir" or "asu" gets hidden </pre>

hide content of files:
<pre> just add a line containing "hiro" at the end of the file </pre>

disables ioctl and ps automatically


Remove the rootkit with:
<pre> bash remove.sh </pre>

WARNGING:
THIS ROOTKIT CAN AND WILL DESTROY THE MACHINE IF YOU DONT USE THE GCC ON THE MACHINE WHERE YOU WANT TO RUN IT  
THERE WERE ALSO PREIOUS ERRORS WHERE THE ROOTKIT KILLED SSH SESSIONS AND TERMINALS  
I DONT TAKE ANY RESPONSIBILITY FOR ANY DAMAGE CAUSED BY THIS ROOTKIT  


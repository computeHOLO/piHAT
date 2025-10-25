# piHAT
Code for Pi Zero that makes a hat with a screen with http-server
# How to Run
Step 1: Install Dependencies  

sudo apt update  

sudo apt install libmicrohttpd-dev fbi ffmpeg mpv build-essential  

Step 2: Create media Directory  

mkdir -p /tmp/media  

Step 3: Compile the Code  

gcc screenhat_server.c -o screenhat_server -lmicrohttpd  

gcc screenhat_daemon.c -o screenhat_daemon  

Step 4: Run the code!  

./screenhat_server  

./screenhat_daemon
Step 5: Access image uploader  

http://pi-ip:8080  

(WILL MAKE AUTO INSTALLER SOON)  

thats it!

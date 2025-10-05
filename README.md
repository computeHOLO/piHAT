# piHAT
Code for Pi Zero that makes a hat with a screen with http-server
# How to Run
Step 1: Install Dependencies\n
sudo apt update\n
sudo apt install libmicrohttpd-dev fbi omxplayer build-essential
Step 2: Create media Directory\n
mkdir -p /tmp/media\n
Step 3: Compile the Code\n
gcc screenhat_server.c -o screenhat_server -lmicrohttpd
gcc screenhat_daemon.c -o screenhat_daemon
Step 4: Run the code!
./screenhat_server
./screenhat_daemon
Step 5: Access image uploader
http://<your-pi-ip>:8080
(WILL MAKE AUTO INSTALLER SOON)
thats it!

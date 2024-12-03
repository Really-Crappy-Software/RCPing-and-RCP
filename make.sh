sudo cp libcap.h /usr/include
sudo cp cap_names.h /usr/include
sudo cp libcap.h /usr/local/include
sudo cp cap_names.h /usr/local/include
gcc rcping.c -o rcping
sudo cp rcping /usr/bin

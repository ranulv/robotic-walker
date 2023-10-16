# Install Git
sudo apt install git

-----------------------------------------------------------------------------------------------
# On some systems, the python --version command may be associated with Python 2.x instead of Python 3.x.  If you want to use Python 3.x by default, you can create an alias for the python command that points to python3. 
gedit ~/.bashrc
alias python='python3'
source ~/.bashrc

-----------------------------------------------------------------------------------------------
# Install python3.7 and create virtual environment

# Add the deadsnakes PPA to your system:
sudo add-apt-repository ppa:deadsnakes/ppa

# Update the package list:
sudo apt-get update

# Install Python 3.7 venv version:
sudo apt-get install python3.7-venv

# navigate to folder
cd ~/robotic-walker

# Once Python 3.7 is installed, you can create a virtual environment using the following command:
python3.7 -m venv venv

# This will create a new virtual environment named myenv that uses Python 3.7. You can activate the virtual environment using the following command:
source myenv/bin/activate

# This will activate the virtual environment and allow you to install packages using pip. When you are finished working in the virtual environment, you can deactivate it using the following command:
deactivate

# extra - To see all versions of Python that are installed on your Ubuntu system, you can run the following command in a terminal:
ls /usr/bin/python*

(# install pip
sudo apt install python3-pip)

-----------------------------------------------------------------------------------------------
# Install ROS Noetic - https://www.youtube.com/watch?v=UGHE7HyzRXw
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt install curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
sudo apt update
sudo apt install ros-noetic-desktop-full
source /opt/ros/noetic/setup.bash
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc

sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential
sudo apt install python3-rosdep
sudo rosdep init
rosdep update

# Verify installation
1/ roscore
2/ rosrun roscpp_tutorials talker
3/ rosrun roscpp_tutorials listener
4/ rostopic list

----------------------------------
# Install Arduino IDE
https://docs.arduino.cc/software/ide-v1/tutorials/Linux
navigate to extracted directory
sudo sh install.sh
sudo usermod -a -G dialout ranulv
log out and log in again for this change to take effect.

# Install ROS packages for Arduino
sudo apt install ros-noetic-rosserial
sudo apt install ros-noetic-rosserial-arduino
sudo apt install ros-noetic-rosserial-python

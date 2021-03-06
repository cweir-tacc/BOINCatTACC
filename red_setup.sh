#!bin/bash

############
# BASICS
#
# Necessary packages to set-up and work with a Redis database to store job submission
############


# Requirements
# |   Ubuntu system, preferably > 16
# |   Docker installed
# |   Internet connection

# Sets up a Redis client on port 6389

apt-get update -y
apt-get install redis-server vim git-core -y
git clone git://github.com/nrk/predis.git
cp predis/* ./user-interface/token_data
# Sets up a redis server on port 6389, which must be open in the docker-compose.yml
redis-server --port 6389 &
# Sets up python3, needed
apt-get install python3 python3-pip python3-mysql.connector -y
# Python modules
pip3 install redis Flask Werkzeug docker ldap3 requests

# Moves all the APIs and email commands
# Requires to be cloned inside project
cp ./api /home/boincadm/project
cp ./adtd-protocol /home/boincadm/project
cp ./email_assimilator.py /home/boincadm/project
cp ./email2.py /home/boincadm/project
cp ./user-interface/* /home/boincadm/project/html/user
cp ./API_Daemon.sh  /home/boincadm/project
cp ./bproc.sh  /home/boincadm/project
cp ./password_credentials.sh /home/boincadm/project
cp ./dockerhub_credentials.sh /home/boincadm/project
cp ./idir.py /home/boincadm/project
cp ./automail.sh /home/boincadm/project
mkdir /home/boincadm/project/adtd-protocol/process_files
mkdir /home/boincadm/project/adtd-protocol/tasks
mkdir /results/adtdp

# Moves the front end files
cp /home/boincadm/project/html/user /home/boincadm/project/html/user_old
#cp ./user/img1 /home/boincadm/project/html/user/
cp ./user /home/boincadm/project/html/user

# Also moves the schedules
cp /home/boincadm/project/html/user_old/schedulers.txt /home/boincadm/project/html/user/schedulers.txt

# Substitutes the project and inc files by their new equivalents
cp /home/boincadm/project/html/inc /home/boincadm/project/html/inc_previous
cp ./inc /home/boincadm/project/html/inc
cp /home/boincadm/project/html/project /home/boincadm/project/html/project_old
cp ./project /home/boincadm/project/html/project
cp /home/boincadm/project/html/user_profile /home/boincadm/project/html/user_profile_old
cp ./user_profile /home/boincadm/project/html/user_profile


chmod +x /home/boincadm/project/email_assimilator.py
chmod +x /home/boincadm/project/api/server_checks.py
chmod +x /home/boincadm/project/api/submit_known.py
chmod +x /home/boincadm/project/api/reef_storage.py
chmod +x /home/boincadm/project/api/MIDAS.py
chmod +x /home/boincadm/project/api/webin.py
chmod +x /home/boincadm/project/API_Daemon.sh
chmod +x /home/boincadm/project/bproc.sh
chmod +x /home/boincadm/project/html/user/token_data/create_organization.py
chmod +x /home/boincadm/project/html/user/token_data/modify_org.py
chmod +x /home/boincadm/project/api/factor2.py
chmod +x /home/boincadm/project/api/harbour.py
chmod +x /home/boincadm/project/api/allocation.py
chmod +x /home/boincadm/project/api/ualdap.py
chmod +x /home/boincadm/project/api/t2auth.py
chmod +x /home/boincadm/project/idir.py
chmod +x /home/boincadm/project/api/personal_area.py
chmod +x /home/boincadm/project/api/envar.py
chmod +x /home/boincadm/project/adtd-protocol/redfile2.py
chmod +x /home/boincadm/project/adtd-protocol/red_runner2.py
chmod +x /home/boincadm/project/api/adtdp_common.py
chmod +x /home/boincadm/project/api/signup_email.py
chmod +x /home/boincadm/project/api/newfold.py
chmod +x /home/boincadm/project/api/midasweb.py
chmod +x /home/boincadm/project/email2.py
chmod +x /home/boincadm/project/automail.sh


# Asks the user to make the main directory available
printf "Enter the apache2.conf and comment out the main directory restrictions\nThis message will stay for 20 s\n"
sleep 20
vi /etc/apache2/apache2.conf

# Updates the scheduler
printf "<!-- <scheduler>http://$URL_BASE/boincserver_cgi/cgi</scheduler> -->\n" > /home/boincadm/project/html/user/schedulers.txt
printf "<link rel=\"boinc_scheduler\" href=\"$URL_BASE/boincserver_cgi/cgi\">" >> /home/boincadm/project/html/user/schedulers.txt


# Adds a DocumentRoot to the approproate configuration file
sed -i "s@DocumentRoot.*@DocumentRoot /home/boincadm/project/html/user/\n@"  /etc/apache2/sites-enabled/000-default.conf

# Changes the master URL to just the root
sed -i "s@<master_url>.*</master_url>@<master_url>$URL_BASE/</master_url>@" /home/boincadm/project/config.xml

# Restarts apache
service apache2 restart


/home/boincadm/project/API_Daemon.sh -up
nohup /home/boincadm/project/bproc.sh &

# Runs the emails on a loop due to cron problems
nohup /home/boincadm/project/automail.sh &

#################################### STATISTICS HAVE BEEN TEMPORARILY DISCONTINUED
# Creates the Redis Tag database
#python3 create_tag_db.py
#sed -i "12iprint('This action will restart the tag database, if you wish to continue, comment this line'); sys.exit()" create_tag_db.py


# Needed to avoid confusion
sleep 2
printf "\nSet-up completed, server is ready now\n"

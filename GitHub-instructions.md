Instructions GitHub Use

Clone a Repository
	1-Copy the URL repository on GitHub webpage
	2-Terminal--> git clone URL
	*-https://help.github.com/articles/cloning-a-repository/#platform-linux

Git Configuration for the cloned respository
	1-Terminal--> git config --global user.name "your GitHub UserName"
	2-Terminal --> git config --global user.email "your_email@domainname.com"

Remembering your username and password
	1-Terminal--> git config --global credential.helper cache
	2-Terminal--> git config --global credential.helper 'cache --timeout=28800'

Compile
	1-Terminal--> Go to the main repository folder
	2-Terminal--> Catkin Build

Commit & Push
	1-Go to the /B212_P1_ROB16/src
		1-Terminal--> git add nodes
	2-Terminal--> git commit -m 'message about the commit'
	3-Terminal--> git push

Pull
	1-Terminal--> git pull

	If pull doesn't work becuase of unresolved conflicts, you can hard reset.
	http://stackoverflow.com/questions/1125968/how-to-force-git-pull-to-overwrite-local-files
		git fetch --all
		git reset --hard origin/master
		WARNING - this forces your local repository to become overwritten by the remote master that you just fetched.

Git Commands and KeyWords in detail
	https://github.com/GarageGames/Torque2D/wiki/Cloning-the-repo-and-working-with-Git

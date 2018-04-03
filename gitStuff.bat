@echo off
ECHO GitHub Commands
ECHO Pulling...
@echo on
git pull
@echo off
PAUSE
ECHO Uploading...
SET message=Standard Commit
SET /p message=Enter a commit message: 
@echo off
call git add .
call git commit -m "%message%"
call git push origin master
#!/bin/sh

echo "# r2" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/vale2/r2.git
git push -u origin master

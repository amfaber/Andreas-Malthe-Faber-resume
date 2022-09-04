Hi! Welcome to my GitHub resume, a repo designed to showcase some of the more interesting code I've been working on so far.

# Python
Python is the langauge with which I am most familiar and have the most experience reading and writing. Most of the projects on here are python. Some of the more notable ones are listed here.

## My fork of EquiBind
EquiBind is a Machine Learning model for docking small molecules to proteins, which I have been using for my [Master's Thesis](https://github.com/amfaber/POR-DD) on using ML to generate drug candidates for a specific protein. The original repo had an implementation for inference which relied on providing molecule-protein pairs, whereas I am interested in docking many molecules to one protein. Because of this, I refactored the loading of the protein and molecules, resulting in two new files in the project, [multiligand_inference.py](https://github.com/amfaber/EquiBind/blob/512bc9b058234d04bea782f3bf8f7e8188e7bb6b/multiligand_inference.py) and [multiple_ligands.py](https://github.com/amfaber/EquiBind/blob/512bc9b058234d04bea782f3bf8f7e8188e7bb6b/datasets/multiple_ligands.py). In addition to not having to duplicate and reload the protein for each molecule, my implementation also supports batching and sending multiple molecules to the GPU simultaneously, providing great speed-ups over the original implementation.

As this functionality had been requested on the orginal EquiBind repo, I submitted a [pull request](https://github.com/HannesStark/EquiBind/pull/37), which has status "closed", but 6 of 7 commits were merged by the creator of EquiBind with git cherry-pick.

## Kattis challenges
In my spare time, I enjoy solving programming challenges such as those presented on [Kattis](open.kattis.com). Most of these problems fall under the category of discrete mathematics and often have trivial "brute force" solutions. The challenge comes from creating a program that passes the tests in less than 1 second runtime. I have compiled the harder problems I have solved in [this folder](https://github.com/amfaber/Andreas-Malthe-Faber-resume/tree/main/Kattis%20problems%20with%20explanations) along with explanations of the solutions. Other Kattis problems I have solved can be found [here](https://github.com/amfaber/Andreas-Malthe-Faber-resume/tree/main/Other%20Kattis%20problems), though these solutions have neither comments nor explicit explanations. On Kattis, each problem has a difficulty rating in the range 1-10. Each problem name is prefixed by the difficulty of the problem at the time they were added to this repo.

## Performance, numpy and pandas
As much of my work on my Master's Thesis deals with fairly large data quantities (>5Gb), delegating these tasks to libraries written in something more performant than python is critical. Through this work, and the performance critical-algorithm challenges from Kattis, I have become very conscious of whether hot loops are delegated to faster libraries or running in (slow) native python. I also have experience with profiling a script and optimizing the hottest parts for a better runtime.

## Bachelors project
I initially learned python through use on my Bachelors Thesis. However, this was before I took the time to properly acquaint myself with git and github, and thus most of the code is lost on a server I no longer have access to.

# Rust
Python is a fantastic multi-tool, but I have at various times run into the limitation of its slow runtime. Usually, this can be alleviated by using appropriate libraries. However, I have recently become more and more interested in writing the code critical code directly in a performant language. When choosing which performant langauge to learn, I had heard only good things about Rust and its community, and thus decided to dedicate some time to learning the language.

I found the experience to be greatly rewarding, and while I initially struggled a lot with the borrow-checker, resolving the issues it highlights ended up teaching me a lot about memory. I also found Rusts multiprocessing to be a breath of fresh air.

## LIT-PCBA-parser
LIT-PCBA is a dataset for benchmarking virtual screening models, which I used for my masters thesis. In order to compare my results to some previous results, I had to sort through a large amout of data (~160Gb when compressed) in a very odd format and extract a subset of it. For this purpose, I ended up writing a parser CLI in Rust. That CLI later got expanded with some other tasks which were useful for my Master's Thesis. During this project, I famliarized myself with general syntax, the borrow-checker, multiprocessing and commandline handling in Rust. The project can be found [here](https://github.com/amfaber/LIT-PCBA-parser).

# C++
Another fast runtime language, C++ was a competitor to Rust for my choice of second language. The main draw of Rust for me was the memory safety guarantees and more modern language structure generally. However, C and C++ also make a compelling case, mostly because of how established the languages already are with huge code-bases written in both C and C++. As such, I have also dabbled in some C++.

## Gnina modifications
Another critical model in my Master's Thesis is [gnina](https://github.com/gnina/gnina), which is written in C++. Initially, just building the project on a server I didn't have root access to was quite the challenge. I eventually got all the dependencies built from source, and was then able to build gnina. As gnina is integrated into the training of a generative model, I ran into a problem much like the one I initially encountered in EquiBind. Constantly calling gnina in the training loop was repeatedly loading both the CNN and the protein, while it would be greatly preferable to keep these two in memory while loading new molecules. As a solution, I made a new option for the gnina CLI: "--continuous-operation", in which the binary doesn't shut down after calculating the molecules, but instead awaits input from stdin. Once anything other than "quit" is received, it is assumed that the supplied input file has been mutated, and the molecules are loaded and scored against the protein again. Once gnina finishes computation, it outputs a specific string to stdout. In the training loop, this binary is called from a python subprocess, and the communication between python and C++ can then be achieved through stdio.

While this setup is a hack, it was quick and preferable to refactoring the very large gnina project into something like a proper python package.

## Ab Initio Kattis problem
My first C++ project was for a [specific Kattis problem](https://github.com/amfaber/Andreas-Malthe-Faber-resume/tree/main/Kattis%20problems%20with%20explanations/7.5%20-%20Ab%20initio) where I could not get the python runtime under 1 second, no matter how many improvements I made to the algorithm. Thus, I decided to implement the algorithm in C++ instead. There was some initial friction, but being able to troubleshoot through the working (slower) implementation in Python was instrumental to debugging the C++ implementation.

# CS 3505 Multi-User Spreadsheet Project
## Installing boost correctly
This project uses the boost asio library extensively for it's networking and asyncrhonous operations. 
The project will work with boost version 1.69.0 and higher. **It's important that the corect version
of boost is used, or else the project will not compile correctly**.  
  
If you want the server to run the CADE lab machines, it's important
that you don't point the compilation to the existing dynamically linked boost libraries, as it is running the wrong version. If you are running the compilation on the CADE machines (or any other machine where you don't have access to write downlaod files to the 
defualt c++ include directory), the following instructions will 
ensure that the project can install correctly.  
  
**Note:** The makefile points very specifically to the directories mentioned below, so it's important that you put the installation in the correct place. 

1. **Clone (or download) the repository, and move to the project**.  
    
    If you haven't already, clone this repository into whichever folder you'd like. Once it's cloned, move into the root of the directory from whichever director you are currently in. 
   ```shell
   cd spreadsheet-server
   ```
2. **Get the path the project**.  

   You will need this path later so make sure you don't lose it. Get the path to the project by running
   ```shell
   pwd
   ```
3. **Get the latest install of boost**.  
  
   The current compressed tar file can be found [here](https://www.boost.org/users/history/version_1_70_0.html) (the latest is 1.70, which will work). 
4. **Extract the boost_1_70_.tar.gz file**.  
  
   Using the shell, work your way to whatever directory you installed the tar.gz (we recommend your home directory) and run the following command (this will extract the libary into a boost_1_70_0 file in the same directory)
   ```shell
   tar -xzvf boost_1_70_0.tar.gz
   ```
5. **Change the directory into boost**
   ```shell
   cd boost_1_70_0
   ```
6. **Configure boost to compile correctly**.

    This is the most important step so make sure to run the commands correctly. Most of boosts libraries are header only, and don't require compilation. However, the system library, which is required for the project, needs to be specifically compiled. The following command tells boost to compile that library, and put it in the right directory of the project. Make sure that you have the directory the project from step 1. Run this command in the extracted boost folder. 
    ```shell
    ./bootstraph.sh --with-libraries=system --prefix=(path_to_project)/libs
7. **Compile and install boost**.  
  
    Boost should be configured to compile correctly now, so the following command will compile and install the needed boost libraries at the correct location. 
    ```shell
    ./b2 install
    ```
8. **Compile and run the project**.  
  
    Move your directory back to the root of the project installation. The /src folder holds all of the source code and makefile that compiles it, and /bin folder holds all of the compiled objects and executables to run. You'll need to move into the /src folder, compile the project, and then move back to /bin/exectuables to run the project. 
    ```shell
    cd src
    make cade
    ```
    If installed correctly, this will put an executable names "server" in the bin/executables folder. This executables takes in the port number the server is listening on as it's only argument. If running on cade, make sure it's port 2112. You'll need to move the /bin folder and run the "server" executable, which will begin the server to start listening for connections. 
    ```shell
    cd ../bin/exectuables
    ./server 2112
    ```

If you've made it this far, the project has been compiled and setup correctly. Feel free to look at and modify the /src/Makefile if needed to accomodate any necessary changes. 

**Note:** The previous steps were written under the assumption that you do not have access to write to the default include paths for c++. If you do have access to those paths, you can install boost there, and instead of running
```shell
make cade
```
you can run 
```shell
make all
```
Either method will install the project correctly. If for any reason you need to clear the binary files, run 
```shell
make clean
```


## Team notes

Here is the link to the documentation for the JSON library

https://github.com/nlohmann/json


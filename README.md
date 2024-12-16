# LogCleaner
Purpose-built to extract information about hashrates, accepted/rejected shares and newly received jobs out of your standard XMRig log-file and saving it to respectively dedicated files.

## What can it do?
> **NOTE:** As of right now it's pretty bare-bones, this will change in the near future.

When run in default mode it will take the specified logfile and extract all lines that contain the hashrate reports with their timestamps.

## How to use
You can run it either manually via command line or append it to your `start.cmd` in the XMRig directory to have it run as soon as XMRig stops and therefore automatically stripping the most recent log-file.

For it to have any data to work with it is **obligatory** to enable log-files in XMRig. You can do this by just appending a `-l yourLogfileNameHere`. It does not need a file extension of any sort.

## Windows
You can either build it yourself from the code in `/source/` or wait for me to upload the compiled executable.

When compiling yourself make sure to use at least `C++17` or newer, since the code utilises the non-experimental `std::filestream` for reading/writing. The code itself was written in a `C++22` environment.

### Manual usage
 1. Open a *CMD* or *Powershell* window
 2. Within the shell navigate to the directory of your `LogCleaner` executable:

```.bat
cd DRIVE:\dir\thatContains\LogCleaner.exe
```
> **NOTE:** This likely is your `Download` directory or your build directory if you compiled yourself

 3. Enter the following line into your command line, replacing the placeholders to your liking:
     
```.bat
LogCleaner.exe path/of/log-file desired/path/of/extract-file filterMode
```

 4. Watch it go through the log-file
 5. Notice the newly appeared file of the specified name in the specified directory 

### Usage via `start.cmd`
To use the LogCleaner from within XMRig we have to quickly set it up for that.

#### Setup
 1. Put the executable into the same directory as `xmrig.exe`
 2. In this directory open the `start.cmd` for editing 
 3. Insert the following line in-between the lines of your `xmrig.exe` setup and the `pause` command and fill in the placeholders to your liking:

```.bat
LogCleaner.exe nameOfLogfile nameOfDesiredOutputFile filterMode
```
 4. Save and close the changed `start.cmd` file

#### Usage
 1. Start up XMRig as you normally would with the `start.cmd`
 2. Mine happily
 3. As soon as you hit `Ctrl`+`C` or close XMRig's window you can watch it go through the generated log-file
 5. Once done, notice the newly generated file of the specified name in the specified directory 
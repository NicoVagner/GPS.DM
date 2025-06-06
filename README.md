# GPS.DM
UNR Derevianko Group GPS Dark Matter project. 

# Introduction
This repo contains most of the code and files used in GPS.DM project over the last 3 years. A full replication of the search to-date is possible with the contents here, with the exception of calculating r (Average of the off diagonal values of the template bank covariance matrix) for the SNR thresholds. UNR peeps: If anyone needs to redo that for whatever reason, reach out to me and I can remake it.

# This repository contains the following
"Previous Work" is entirely the creation of people before me, but is useful or necessary to rerun the search from scratch. 

"vector_search" is the version of the program containing my modifications to the output format, which was necessary for various post processing and false positive filtering ideas we persued. "vector_search baseline" is the most recent version of the search program for which the output is the same as that used for older group papers. My modifications to the formatting mostly invovled outputting all filter-passing templates corresponding to each event, rather than the best fitting template. The E^-1 matrices also get output to a folder. In-program changes would be necessary to make the program run on a new computer, since some input and output directories are hard coded.

The search program includes various external side programs and tools, such as dataConvert, which converts between GPS Day values and UTC dates. Since the search program will most likely fail to compile if any of it's requirements are not met, I have included the compiled version of everything, mostly to provide these tools, which require far less setup than the core search program, but will also fail to compile if it fails to compile.

If you want to run parameter estimation, you must change both the variable in the search.dat configuraiton file, and the m_investigate variable in SearchClass.cpp, then recompile. Various interesting things will happen if these two variables do not agree, with the most likely being that you will get most output values rounded down to ~10^-300, or up to ~10^300. 

The search program requires the PSD and ACF files to run, which are both provided in the repo under "PSD", as well as the archival clock data files, which are not, due to their immense size. 

"SDD" was a python GUI designed to make inputting information into the search.dat configuration file, it was never quite completed, due to the difficulty of making it work reliably over SSH. Any change to the whitespace of search.dat will almost certainly break the search program.

"Post Processing Concepts" is a series of programs I created to try out various ideas of using known limitations of the search or what we believed to be causes of false positives to rule out events. fc (file copy) is used to copy the chi threshold values from one set of files to another. chi2 is then used to generate a list of events that exceed their chi2 thresholds. rec is used to then delete all event templates on that list. overflip creates a list of events that either overlap, or where the SNR flips signs (Say, -6.37 to 6.41) in the same epoch. rec is again used to delete all events (not the individual versions from different templates, but all versions of an event) from that list. snrThres was used to apply the SNR threshold, before I learned bash enough to realize I could more easily do it that way. ChiT similarly deletes events that exceed the chi^2 threshold. overlap is a precursor to overflip (Portmanteau between overlap and flip. It turned out to be easier to modify overlap than to make a new program). bash.txt was just a list of commands needed to run all of these, to copy and paste instead of retyping or finding in shell history.

"Mathematica" contains various notebooks I created, either to recalculate specific (SNR threshold, Chi^2 threshold), or to produce visualizations.

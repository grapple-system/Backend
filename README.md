# Grapple Backend

Welcome to the home repository of Grapple Backend.

Grapple is a path-sensitive finite-state property checking graph system via constraint-guided CFL reachability. This repository is the backend of Grapple.

This Readme (under revision) provides a how-to-use guide for Grapple Backend.

For a detailed description of our system, please see our paper, which has been accepted at EuroSys'19.

## Getting Started

Grapple Backend is simple to use, with a very straight-forward compilation procedure.

### Required Libraries
Ensure that you have a recent version of the Boost library and the Z3 theorem prover installed in your system. We used Boost 1.67.0, Z3 4.8.0 and g++ 5.4.0 in our experiments.

### Compiling Grapple-backend
First, download the entire Backend source code into your machine. 
Next, edit the engine/src/makefile to set the paths to the Boost library and the Z3 include files and lib files in your machine. Finally, run the makefile using make. Grapple-backend should now be compiled and ready to run.

### Running Grapple-backend

Grapple-backend needs three input files: (1) a graph on which Grapple-backend can perform computations, (2) a grammar file which the sequence of the labels on the path has to match and (3) a smt2 file which is used to decode the PseudoPCs.

A sample input is inside the engine/src/inputFiles folder.

After getting the above files, run the engine/src/run script in your command line as shown below,

```
./run <graph_file> <grammar_file> <smt2_file> <number_partitions> <memory_budget> <number_threads>
```

After running the above command, you can monitor the progress of the computation by viewing the generated output file in the engine/src/log folder.

## Project Contributors

* [**Zhiqiang Zuo**](http://zuozhiqiang.bitbucket.io/) - *Assistant Professor, Nanjing University*
* **Yifei Wang** - *Master Student, Nanjing University*
* **Qiuhong Pan** - *Master Student, Nanjing University*
* **Shenming Lu** - *Master Student, Nanjing University*

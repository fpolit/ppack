## Command to compile manually `PPACK`

### OpenMP Version
* g++ cmd to compile statsgen (run inside src directory)
```bash
g++  -std=c++17 statsgen.cpp pstructs.cpp mask.cpp ppack.cpp password.cpp basepoli.cpp csv.cpp fineprint.cpp logos.cpp -lboost_program_options -fopenmp -o statsgen 
```

* g++ cmd to compile maskgen (run inside src directory)
```bash
g++  -std=c++17 maskgen.cpp pstructs.cpp mask.cpp ppack.cpp password.cpp csv.cpp basepoli.cpp fineprint.cpp logos.cpp -lboost_program_options -fopenmp -o maskgen
```

* g++ cmd to debug policygen (run inside src directory)
```bash
g++ -std=c++17 policygen.cpp mask.cpp password.cpp pstructs.cpp basepoli.cpp ppack.cpp csv.cpp fineprint.cpp logos.cpp  -lboost_program_options -fopenmp -o policygen
```

### Uniprocessor version
* g++ cmd to compile statsgen (run inside src directory)
```bash
g++ -O2 -std=c++17 statsgen.cpp pstructs.cpp mask.cpp ppack.cpp password.cpp basepoli.cpp csv.cpp fineprint.cpp logos.cpp -lboost_program_options -o statsgen 
```

* g++ cmd to compile maskgen (run inside src directory)
```bash
g++  -O2 -std=c++17 maskgen.cpp pstructs.cpp mask.cpp ppack.cpp password.cpp csv.cpp basepoli.cpp fineprint.cpp logos.cpp -lboost_program_options -o maskgen
```

* g++ cmd to debug policygen (run inside src directory)
```bash
g++ -O2 -std=c++17 policygen.cpp mask.cpp password.cpp pstructs.cpp basepoli.cpp ppack.cpp csv.cpp fineprint.cpp logos.cpp  -lboost_program_options -o policygen
```



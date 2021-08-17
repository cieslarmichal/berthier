# berthier
Application for budgeting that controls money transactions directly from bank account


Setup mongo driver on Ubuntu:

```apt-get install libmongoc-1.0-0```

```sudo apt-get install cmake libssl-dev libsasl2-dev```

```
wget https://github.com/mongodb/mongo-c-driver/releases/download/1.18.0/mongo-c-driver-1.18.0.tar.gz
tar xzf mongo-c-driver-1.18.0.tar.gz
cd mongo-c-driver-1.18.0
mkdir cmake-build
cd cmake-build
cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
```

```
cmake --build .
sudo cmake --build . --target install
```

```
curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.5/mongo-cxx-driver-r3.6.5.tar.gz
tar -xzf mongo-cxx-driver-r3.
tar -xzf mongo-cxx-driver-r3.6.5.tar.gz
cd mongo-cxx-driver-r3.6.5/build
```

```cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local```

```sudo cmake --build . --target EP_mnmlstc_core ```

```
cmake --build .
sudo cmake --build . --target install
```
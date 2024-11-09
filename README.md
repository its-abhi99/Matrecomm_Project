
# YugabyteDB Connector Project

## Overview

This project implements a **C++ connector** using **Poco C++ libraries** to interact with **YugabyteDB**, a distributed SQL database. The connector provides functionalities such as authentication, query execution, and error handling. It supports operations for managing employee data, including adding, retrieving, and modifying records in YugabyteDB.

## Prerequisites

Before running this project, ensure that you have the following software installed:

- **Ubuntu 20.04+**
- **CMake** (version 3.10 or higher)
- **Poco C++ Libraries** (Foundation, Data, DataPostgreSQL)
- **PostgreSQL** client libraries
- **YugabyteDB** (installed or running via Docker)
- **GCC/G++** (C++17 support)

---

## Setup and Build

Follow these steps to clone, build, and run the project:

### Step 1: Clone the Repository

```bash
git clone https://github.com/its-abhi99/Matrecomm_Project.git
cd yugabyte-connector
```

### Step 2: Install Dependencies

Install **Poco** and **PostgreSQL** libraries in root(e.g desktop)

```bash
sudo apt update
sudo apt install libpoco-dev libpq-dev
```

Install **CMake** (if not already installed):

```bash
sudo apt install cmake
```

### Step 3: Build the Project

Create a `build` directory and compile the project:

```bash
mkdir build
cd build
cmake ..
make
```

This will generate test executables for `main_test` and `employee_management_test`.

---

## Install and Configure YugabyteDB

Follow these steps to install and configure **YugabyteDB** on **Ubuntu**:

### Step 1: Install Required Packages

- **Python**: Check if Python 3 is installed:

    ```bash
    python --version
    ```

    If Python is not installed:

    ```bash
    sudo apt install python-is-python3
    ```

- **Wget** (for downloading YugabyteDB):

    ```bash
    sudo apt install wget
    ```

### Step 2: Download and Install YugabyteDB

1. Download the YugabyteDB package:

    ```bash
    wget https://downloads.yugabyte.com/releases/2.23.0.0/yugabyte-2.23.0.0-b710-linux-x86_64.tar.gz
    ```

2. Extract the package and navigate to the YugabyteDB directory:

    ```bash
    tar xvfz yugabyte-2.23.0.0-b710-linux-x86_64.tar.gz
    cd yugabyte-2.23.0.0/
    ```

3. Run the post-install script:

    ```bash
    ./bin/post_install.sh
    ```

### Step 3: Start YugabyteDB Cluster

Create a single-node local cluster:

```bash
./bin/yugabyted start
```

The output should indicate the cluster status:

```text
Status: Running
YugabyteDB UI: http://127.0.0.1:15433
JDBC: jdbc:postgresql://127.0.0.1:5433/yugabyte
```

To check the cluster status:

```bash
./bin/yugabyted status
```

```if text
Status: Bootstrapping
```
```bash
./bin/yb-ctl start
```

In my CASE I STUCK HERE AND RESOLVE !! see below
```markdown
# YugabyteDB Setup Instructions

## Overview
This document provides instructions to set up YugabyteDB on a Linux system and handle common setup issues.

## Starting YugabyteDB
To start YugabyteDB, use the following command:

```bash
./bin/yugabyted start
```

Upon starting, you should see output similar to this:
```
Starting yugabyted...
✅ YugabyteDB Started
✅ UI ready
✅ Data placement constraint successfully verified
⚠ WARNINGS:
- ntp/chrony package is missing for clock synchronization. For centos 7, we recommend installing either ntp or chrony package and for centos 8, we recommend installing chrony package.
- Cluster started in an insecure mode without authentication and encryption enabled. For non-production use only, not to be used without firewalls blocking the internet traffic.

🚀 YugabyteDB started successfully! To load a sample dataset, try 'yugabyted demo'.
```

### Important URLs and Information
- **YugabyteDB UI**: [http://127.0.1.1:15433](http://127.0.1.1:15433)
- **JDBC**: `jdbc:postgresql://127.0.1.1:5433/yugabyte?user=yugabyte&password=yugabyte`
- **YSQL Shell**: `bin/ysqlsh -h 127.0.1.1 -U yugabyte -d yugabyte`
- **YCQL Shell**: `bin/ycqlsh 127.0.1.1 9042 -u cassandra`
- **Data Directory**: `/home/abhisk/var/data`
- **Log Directory**: `/home/abhisk/var/logs`

### Checking Status
To check the status of YugabyteDB, run:

```bash
./bin/yugabyted status
```

Expected output:
```
+---------------------------------------------------------------------------------------------------+
|                                             yugabyted                                             |
+---------------------------------------------------------------------------------------------------+
| Status         : Bootstrapping or Running (depending on state)                                    |
| YugabyteDB UI  : http://127.0.1.1:15433                                                           |
| JDBC           : jdbc:postgresql://127.0.1.1:5433/yugabyte?user=yugabyte&password=yugabyte        |
| YSQL           : bin/ysqlsh -h 127.0.1.1 -U yugabyte -d yugabyte                                  |
| YCQL           : bin/ycqlsh 127.0.1.1 9042 -u cassandra                                           |
| Universe UUID  : [Unique Identifier]                                                              |
+---------------------------------------------------------------------------------------------------+
```

### Common Issues and Fixes

#### 1. Missing Python Dependency
If you see an error related to Python, create a symbolic link to Python3:
```bash
sudo ln -s /usr/bin/python3 /usr/bin/python
```

#### 2. Locale Issues
If you encounter locale issues, configure locales with the following:
```bash
sudo locale-gen en_US.UTF-8
sudo dpkg-reconfigure locales
```

To verify, run:
```bash
locale -a
```

### Additional Tools
To manage the cluster, you can also use `yb-ctl`:

```bash
./bin/yb-ctl start
```

This will start the cluster with default settings, and you can check the cluster's status by running:
```bash
yb-ctl status
```


### Step 4: Connect to YugabyteDB

Use `ysqlsh` to connect to your local YugabyteDB instance:

```bash
./bin/ysqlsh
```

Once connected, you can interact with the database via SQL commands:

```text
ysqlsh (11.2-YB-2.23.0.0-b0)
Type "help" for help.
yugabyte=#
```

---

## Running Tests

After building the project, run the following test executables to validate the functionality:

1. **Employee Management Test:**

    ```bash
    .cd/yugabyte-connector/build/employee_management_test
    ```

2. **Main Test:**

    ```bash
    ./build/main_test
    ```

---

## License

This project is licensed under the MIT License. See the LICENSE file for more details.

---

This **README.md** file provides a complete guide to setting up and running the YugabyteDB Connector project, including instructions for installing YugabyteDB, building the project, and running tests.
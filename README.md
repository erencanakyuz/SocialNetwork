# Social Network Analyzer

## Description

This C++ project implements a social network analyzer that allows you to load social network data from a CSV file, display network information, suggest friends based on different criteria, calculate network metrics like degree centrality and clustering coefficient, and detect communities using the Girvan-Newman algorithm.

## Building

To build the project, you will need a C++ compiler (like g++) and `make`.

1.  **Navigate to the project directory** in your terminal.
2.  **Compile the code:** You can use the following command to compile the `main.cpp`, `Graph.cpp`, and `Person.cpp` files:

    ```bash
    g++ main.cpp Graph.cpp Person.cpp -o social_network_analyzer
    ```

    This command will create an executable file named `social_network_analyzer` in your project directory.

## Running

1.  **Make sure you have a CSV data file** named `social_network.csv` in the project directory or provide the correct path when running the analyzer. The CSV file should contain social network data in a format that the `readData` function in `Graph.cpp` can parse (the format is not specified in the provided code, you might need to adjust this based on your actual data format).
2.  **Run the executable:** Execute the compiled program using the following command in your terminal:

    ```bash
    ./social_network_analyzer
    ```

## Usage

Once the program is running, you will be presented with a menu with the following options:

1.  **Display the social network:** Shows the details of all users in the network, including their ID, name, age, gender, occupation, and friends.
2.  **Suggest friends:**  Provides friend suggestions for a given user based on:
    *   **1. By Common Friends:** Suggests friends based on mutual connections.
    *   **2. By Occupation:** Suggests friends with the same occupation.
    *   **3. By Age:** Suggests friends of the same age.
3.  **Calculate degree centrality for any user:** Calculates and displays the degree centrality of a specified user. Degree centrality is the number of friends a person has.
4.  **Calculate clustering coefficient:** Calculates and displays the clustering coefficient for a specified user. The clustering coefficient measures the degree to which friends of a given user are friends with each other.
5.  **Detect communities using the Girvan-Newman algorithm:**  Applies the Girvan-Newman algorithm to detect communities within the social network. You will be prompted to enter the number of iterations for the algorithm.
6.  **Exit:**  Terminates the program.

**Example Interaction:**

auto start = chrono::high_resolution_clock::now();

auto stop = chrono::high_resolution_clock::now();

cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(stop - start).count() << " ms." << endl;
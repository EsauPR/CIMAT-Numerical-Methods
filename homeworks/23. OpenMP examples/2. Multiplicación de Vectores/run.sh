rm time.txt
for cores in {1..12}; do
    for size in 1000000000; do
        { /usr/bin/time -f "Cores: $cores: InputSize: $size Time %es Memory: %MKb CPU: %P" ./a.out $size $cores; } 2>> time.txt
    done;
done;

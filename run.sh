rm -rf main
rm -rf log.txt
g++ -o main *.cpp
cat testInput.txt | ./main > log.txt

if [ -f "log.txt" ]; then
  CHECK=$(diff -b -B log.txt result.txt)
  if [ "$CHECK" !=  "" ]; then
    echo "FAIL"
  else
    echo "PASS"
  fi
else
  echo "FAIL (MISSING FILE)"
fi

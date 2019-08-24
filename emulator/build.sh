pushd ../processor
python process.py
popd
make -f makefile.linux

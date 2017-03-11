
mkdir -p data

# Try to download the data
RES=`wget -O data/cornell.zip 'http://www.mpi-sws.org/~cristian/data/cornell_movie_dialogs_corpus.zip'`
if [ $? -ne 0 ]; then
	echo "failed to download data - the link might be broken.."
	exit 1
else
	echo "downloaded corpus source"
fi

# unpack the file we need
RES=`unzip data/cornell.zip -d data`
if [ $? -ne 0 ]; then
	echo "failed to unpack files"
	exit 1
else
	echo "unzipped file"
fi

# run the importer
RES=`python2 importcorpus.py data/cornell\ movie-dialogs\ corpus/movie_lines.txt`
if [ $? -ne 0 ]; then
	echo "failed to preprocess corpus"
	exit 1
else
	echo "preprocessed corpus"
fi

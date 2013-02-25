input=/usr/local/cs/jdk1.7.0_13/jre/lib/rt.jar

echo "gzip:"
time gzip <$input >gzip.gz
echo "pigz:"
time pigz <$input >pigz.gz
echo "Jpigz:"
time java Jpigz -i  <$input >Jpigz.gz
ls -l gzip.gz pigz.gz Jpigz.gz
ls -l $input
# This checks Jpigz's output.
pigz -d <Jpigz.gz | cmp - $input

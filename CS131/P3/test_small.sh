echo "gzip:"
gzip <test_file >gzip.gz 
echo
echo "pigz:"
pigz <test_file >pigz.gz
echo
echo "Jpigz:"
java Jpigz -p 1 <test_file >Jpigz.gz
ls -l gzip.gz pigz.gz Jpigz.gz
# This checks Jpigz's output.
gzip -d <Jpigz.gz | cmp - test_file

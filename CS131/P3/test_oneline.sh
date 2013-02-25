echo "gzip:"
time gzip <test_oneline >gzip.gz
echo "pigz:"
time pigz <test_oneline >pigz.gz
echo "Jpigz:"
time java Jpigz -p 1 <test_oneline >Jpigz.gz
ls -l gzip.gz pigz.gz Jpigz.gz
# This checks Jpigz's output.
gzip -d <Jpigz.gz | cmp - test_oneline

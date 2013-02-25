#!/bin/bash
sed 's/\r//g' | 
tr -d '[:blank:]' |
sed 's/<u>//g' |
sed 's/<\/u>//g' | 
sed 's/<b>//g' |
sed 's/<\b>//g' |
sed '/<tr>/,/<\/td>/d' |
sed 's/<tr>//g' |
sed 's/<\/tr>//g' | 
grep '^<td>.*<\/td>$' |
sed 's/<td>//g' |
sed 's/<\/td>//g' |
sed '/^$/d' |
sed s/\`/\'/g |
sed 's/,/\n/g' |
tr '[:upper:]' '[:lower:]' |
grep '[pkmnwlhaeiouPKMNWLHAEIOU]' |
sort |
uniq -u

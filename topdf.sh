#!/bin/bash

for file in src/*
do
    base=$(basename $file)
    new_file=pdf/${base/%/.html}
    vim -c "TOhtml|saveas! $new_file|qa" $file
    wkhtmltopdf $new_file ${new_file/.html/.pdf}
    rm $new_file
done

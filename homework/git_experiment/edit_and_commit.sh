#!/usr/bin/env bash

for commit_count in {2..100}
do
  let linenum="10+$commit_count"
  # Fill in
  sed -i "$linenum i This is the sentence number $commit_count." foo.tex
done

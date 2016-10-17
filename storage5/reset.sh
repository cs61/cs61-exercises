#!/bin/bash

sed -e 's/A/X/g' -e 's/B/X/g' data.in > data.out
mv data.out data.in

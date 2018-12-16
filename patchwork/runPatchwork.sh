#hdfs dfs -mkdir -p /datasets && hdfs dfs -put datasets/Compound.csv /datasets/
/home/luis/Desktop/apache/spark-2.2.0-bin-hadoop2.7/bin/spark-submit --class PatchWorkDemo --master local[4] bin/patchwork_2.11-1.1.jar

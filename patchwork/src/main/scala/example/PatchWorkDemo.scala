import ca.crim.spark.mllib.clustering._
import org.apache.spark.rdd.RDD
import org.apache.spark.{ SparkContext, SparkConf }
import java.io._

object PatchWorkDemo extends App {
  val sc = new SparkContext(new SparkConf()
    .setAppName("PatchworkDemo")
  )

  // Reading and parsing Data
  val dataRDD: RDD[Array[Double]] = sc.textFile("Test.csv")
    .map(_.split(",")).map(s => Array(s(0).toDouble, s(1).toDouble)).cache

  // PatchWork parameters 0.4,0.4
  val epsilon = Array(6.0, 6.0)
  val minPts = 1
  val minCellInCluster = 30
  val ratio = 0.0

  // Training a model with the data
  val (patchworkModel, execTime) = Utils.time(
    new PatchWork(epsilon, minPts, ratio, minCellInCluster).run(dataRDD)
  )

  val bw = new PrintWriter(new File("plotear.dat"))

  // Display the cluster for each data point
  dataRDD.collect().map(x =>
    bw.write(x(0) + " " + x(1) + " " + patchworkModel.predict(x).getID + "\n"))
  bw.close
  // Display some stats about the clusters
  var cs = ""
  for (i <- Range(0, patchworkModel.clusters.size)) {
    cs = cs + "   cluster " + patchworkModel.clusters(i).getID + " has " + patchworkModel.clusters(i).cellsList.size + " cells \n"
  }
  println("\n----------------------------------------- \n" +
    "number of points : " + dataRDD.count() + "\n" +
    "number of clusters : " + patchworkModel.clusters.size + "\n" +
    "----------------------------------------- \n" +
    cs +
    "----------------------------------------- \n" +
    "size of epsilon : [" + epsilon.mkString(",") + "] \n" +
    "min pts in each cell : " + minPts + "\n" +
    "time of training : " + execTime + " ms" + "\n----------------------------------------- \n")

  sc.stop
} // eo PatchWorkDemo

object Utils {
  /**
   * Executes the given function and reports the running time
   *
   * @param f The function to run
   * @tparam A Type returned by the given function
   * @return A pair with the function output and the time in milliseconds
   */
  def time[A](f: => A): (A, Long) = {
    val s = System.currentTimeMillis()
    val ret = f
    (ret, System.currentTimeMillis() - s)
  }
}


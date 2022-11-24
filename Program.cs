using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;

namespace MoveNRename
{
    class Program
    {
        static void Main(string[] args)
        {
            var mask = args[0];
            var search_dir = args[1];
            var dest_dir = Directory.GetCurrentDirectory();

            var files = Directory.GetFiles(search_dir,mask,SearchOption.AllDirectories);

            foreach (string f in files) {
                var fi = new FileInfo(f);
                var path = fi.DirectoryName;
                var name = fi.Name;
                var lastdel = path.LastIndexOf("\\");
                var newname = path.Substring(lastdel+1) + "_" + name;
                Console.Write("Found file '" + name + "'. New name: " + dest_dir + "\\" + newname + Environment.NewLine);
                File.Move(f, dest_dir + "\\" + newname);
            }
        }
    }
}

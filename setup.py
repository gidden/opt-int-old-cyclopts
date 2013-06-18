import os
import subprocess
import shutil

try:
    import argparse as ap
except ImportError:
    import pyne._argparse as ap

def check_windows_cmake(cmake_cmd):
    if os.name == 'nt':
        files_on_path = set()
        for p in os.environ['PATH'].split(';')[::-1]:
            if os.path.exists(p):
                files_on_path.update(os.listdir(p))
        if 'cl.exe' in files_on_path:
            pass
        elif 'sh.exe' in files_on_path:
            cmake_cmd += ['-G "MSYS Makefiles"']
        elif 'gcc.exe' in files_on_path:
            cmake_cmd += ['-G "MinGW Makefiles"']
        cmake_cmd = ' '.join(cmake_cmd)

def install_cyclopts(args):
    if not os.path.exists(args.buildDir):
        os.mkdir(args.buildDir)
    elif args.replace:
        shutil.rmtree(args.buildDir)
        os.mkdir(args.buildDir)
        
    root_dir = os.path.split(__file__)[0]
    src_dir = os.path.join(root_dir, 'src')
    makefile = os.path.join(args.buildDir, 'Makefile')

    if not os.path.exists(makefile):
        cmake_cmd = ['cmake', os.path.abspath(src_dir)]
        if args.prefix:
            cmake_cmd += ['-DCMAKE_INSTALL_PREFIX=' + os.path.abspath(args.prefix)]
        if args.coinRoot:
            cmake_cmd += ['-DCOIN_ROOT_DIR=' + os.path.abspath(args.coinRoot)]
        check_windows_cmake(cmake_cmd)
        rtn = subprocess.check_call(cmake_cmd, cwd=args.buildDir, shell=(os.name=='nt'))

    make_cmd = ['make']
    if args.threads:
        make_cmd += ['-j' + str(args.threads)]
    make_cmd += ['install']
    rtn = subprocess.check_call(make_cmd, cwd=args.buildDir, shell=(os.name=='nt'))        

def main():
    description = "Install Cyclopts. Optional arguments include a path to "+\
        "the Cyclopts source, an installation prefix path and a path to "+\
        "the coin-OR libraries."
    parser = ap.ArgumentParser(description=description)

    buildDir = 'where to place the build directory'
    parser.add_argument('--buildDir', help=buildDir, default='build')

    replace = 'whether or not to remove the build directory if it exists'
    parser.add_argument('--replace', type=bool, help=replace, default=True)

    threads = "the number of threads to use in the make step"
    parser.add_argument('-j', '--threads', type=int, help=threads)

    install = "the relative path to the installation directory"
    parser.add_argument('--prefix', help=install)

    coin = "the relative path to the Coin-OR libraries directory"
    parser.add_argument('--coinRoot', help=coin)

    install_cyclopts(parser.parse_args())        

if __name__ == "__main__":
    main()

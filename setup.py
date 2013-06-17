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
    root_dir = os.getcwd()
    build_dir = os.path.join(root_dir, 'build')
    src_dir = os.path.join(root_dir, 'src')

    if not os.path.exists(build_dir):
        os.mkdir(build_dir)
    elif args.replace:
        shutil.rmtree(build_dir)
        os.mkdir(build_dir)
    os.chdir(build_dir)
        
    makefile = os.path.join(build_dir, 'Makefile')
    if not os.path.exists(makefile):
        
        cmake_cmd = ['cmake', src_dir]
        if args.prefix:
            install_dir = os.path.join(root_dir, args.prefix)
            cmake_cmd += ['-DCMAKE_INSTALL_PREFIX=' + install_dir]
        if args.coinRoot:
            coin_dir = os.path.join(root_dir, args.coinRoot)
            cmake_cmd += ['-DCOIN_ROOT_DIR=' + coin_dir]

        check_windows_cmake(cmake_cmd)
        rtn = subprocess.check_call(cmake_cmd, cwd=build_dir, shell=(os.name=='nt'))

    make_cmd = ['make']
    if args.threads:
        make_cmd += ['-j' + str(args.threads)]
    make_cmd += ['install']
    rtn = subprocess.check_call(make_cmd, cwd=build_dir)
    os.chdir(root_dir)

def main():
    description = "Install Cyclopts. Optional arguments include a path to "+\
        "the Cyclopts source, an installation prefix path and a path to "+\
        "the coin-OR libraries."
    parser = ap.ArgumentParser(description=description)

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

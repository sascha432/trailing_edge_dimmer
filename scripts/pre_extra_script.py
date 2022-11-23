Import("env");
import re
import click
from os import path

print_cpp = path.abspath(env.subst(''))

def process_node(node):
    if re.search(r'[/\\]FrameworkArduino[/\\]Print\.cpp\Z', node.get_abspath()):
        print_h = node.srcnode().get_abspath()[0:-3] + 'h'
        with open(print_h, 'r') as file:
            if file.read().find('friend void __debug_printf(const char *format, ...);')==-1:
                click.secho('File not patched. Run following command:', fg='yellow')
                cmd = 'patch -i %s %s' % (path.abspath(env.subst('$PROJECT_DIR/scripts/Print.diff')), print_h)
                click.echo()
                click.echo(cmd)
                click.echo()
                env.Exit(1)
    return node

env.AddBuildMiddleware(process_node)


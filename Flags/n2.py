import os
from argparse import ArgumentParser

MAX_FUNC_LEN = 20
MAX_NESTING = 5

OPERATORS = '><=!+-*/%&|^ '
TYPES = ('int', 'float', 'bool', 'double', 'short', 'long', 'void')


class StyleParser:
    def __init__(self, file_path):
        self.file_path = file_path
        self.brackets = self.line_num = self.func_len = self.indent_style = 0
        self.line = self.flen_func = self.nest_func = ''
        self.funcs = []
        self.funcs_tested = []
        self.types = list(TYPES)

    def err(self, type, func=False):
        line = self.line.replace('\n', '')
        i=0
        for i, c in enumerate(line):
            if c == ' ':
                continue
            break
        line = line[i:]

        if len(line) > 30:
            line = f'{line[:30]}...'

        prefix = f'[{type.upper()} at line {self.line_num}]'

        print(f'{prefix: <25}{self.funcs[-1] if func else line}')

    def start_of_new_function(self):
        if not self.brackets:
            for dt in self.types:
                if self.line.startswith(dt):
                    break
            else:
                return
            idx = self.line.index(' ')+1
            self.funcs.append(self.line[idx:].replace('\n', ''))
            self.func_len = 0

    def update_brackets(self):
        for c in self.line:
            if c == '{':
                self.brackets += 1
            elif c == '}':
                self.brackets -= 1

    def check_flen(self):
        if self.brackets:
            self.func_len += 1
            if self.func_len > MAX_FUNC_LEN and self.flen_func != self.funcs[-1]:
                self.flen_func = self.funcs[-1]
                self.err('funclen', func=True)

    def check_nesting(self):
        if self.brackets > MAX_NESTING and self.nest_func != self.funcs[-1]:
            self.nest_func = self.funcs[-1]
            self.err('nesting')

    def check_banned_statements(self):
        for statement in ('continue', 'break', 'goto'):
            if statement in self.line:
                self.err('continue/break/goto')

    def check_tabs(self):
        if '\t' in self.line:
            self.err('tabs')

    def check_magicnums(self):
        for num in range(2, 10):
            if str(num) in self.line:
                idx = self.line.index(str(num))

                before = self.line[idx-1]
                after = self.line[idx+1]

                if before.isalpha() or after.isalpha():
                    return
                if before in OPERATORS+'[]' or after in OPERATORS+'[]':
                    self.err('magicnum')
                    return

    def check_includes(self):
        if self.line.startswith('#include') and '<' not in self.line:
            l = self.line.replace("\n", "")
            path = l[l.index("e")+2:].replace('"', "")

            main_path = self.file_path
            for i in reversed(range(len(self.file_path))):
                if self.file_path[i] == '/':
                    main_path = self.file_path[:i+1]
                    break

            file_dir = os.path.join(main_path, path)

            if not os.path.exists(file_dir):
                raise FileNotFoundError(f"File {file_dir} was not found.")

            with open(file_dir) as f:
                line = f.readline()
                while line:
                    val = self.check_typedefs(line)
                    if val:
                        print(f'found "{val}" in {l[l.index("e")+2:]}')
                    line = f.readline()

            # print(f'checking include file {l[l.index("e")+2:]}')
            return True

    def check_typedefs(self, line: str):
        if 'typedef' in line:
            last = line.index('\n')
            line = line[:last]
            if line[-1] == ';':
                first = ''
                for i in reversed(range(len(line))):
                    if line[i] == ' ':
                        first = i+1
                        break
                line = line[first:-1]
                if line not in self.types:
                    self.types.append(line)
                    return line
            elif line[-1] == '{':
                line = line[:-1]
                first = ''
                for i in reversed(range(len(line))):
                    if i < len(line)-1 and line[i] == ' ':
                        first = i+1
                        break
                line = line[first:]
                if line not in self.types:
                    self.types.append(line)
                    return line

    def check_comments(self):
        i=0
        for i, c in enumerate(self.line):
            if c == ' ':
                continue
            break

        if len(self.line) > i+1 and self.line[i+1] == '/':
            return True
        return False

    def check_llen(self):
        if self.line.index('\n') >= 60:
            self.err('linelen')
            return True
        return False

    def check_indentation(self):
        if self.line[0] != ' ':
            return
        count = 0
        for c in self.line:
            if c == ' ':
                count += 1
            else:
                break
        if not count:
            return
        if not self.indent_style:
            self.indent_style = count

        elif count % self.indent_style != 0:
            self.err('indentstyle')

    def start(self):
        within_test_func = False

        with open(self.file_path) as f:
            self.line = f.readline()


            while self.line:
                self.line_num += 1

                if self.check_comments():
                    self.line = f.readline()
                    continue

                if self.check_includes():
                    self.line = f.readline()
                    continue

                self.start_of_new_function()
                self.update_brackets()
                self.check_indentation()

                if within_test_func and not self.brackets:
                    within_test_func = False

                if within_test_func:
                    for s in self.funcs:
                        s = s[:s.index('(')]
                        if s not in self.funcs_tested and s in self.line:
                            self.funcs_tested.append(s)

                if self.funcs and 'test(void)' in self.funcs[-1]:
                    self.line = f.readline()
                    within_test_func = True
                    continue

                self.check_flen()
                self.check_llen()
                self.check_nesting()
                self.check_banned_statements()
                self.check_tabs()
                self.check_magicnums()

                self.line = f.readline()


        untested = [f[:f.index('(')] for f in self.funcs if f[:f.index('(')] not in self.funcs_tested and f != 'test(void)']
        print(f'[UNTESTED FUNCTIONS] {", ".join(untested)}')


parser = ArgumentParser()


parser.add_argument('file', type=str, help='path to .c file')
a = parser.parse_args()
if not a.file:
    raise ValueError('usage: python n2.py <file path>')


p = StyleParser(a.file)
p.start()
# [print(f) for f in p.funcs]







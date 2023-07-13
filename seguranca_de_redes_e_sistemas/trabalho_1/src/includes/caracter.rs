
    pub static TOTAL: &str = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    trait Somar {
        fn add_inteiro(self, valor: isize) -> Option<isize>;
    }
    impl Somar for usize {
        // add code here
        fn add_inteiro(self, valor: isize) -> Option<isize> {
            Some(self as isize + valor)
        }
    }
    pub trait Shift {
        fn somar_valor(self, valor: isize) -> Option<char>;
    }
    trait Indice {
        fn buscar(self) -> Option<char>;
    }
    impl Indice for isize {
        // add code here
        fn buscar(self) -> Option<char> {
            TOTAL.chars().nth(self as usize)
        }
    }
    impl Shift for char {
        fn somar_valor(self, valor: isize) -> Option<Self> {
            if TOTAL.contains(self) {
                return TOTAL
                    .chars()
                    .position(|c| c == self)?
                    .add_inteiro(valor)?
                    .wrapping_rem_euclid(62)
                    .buscar();
            }
            Some(self)
        }
    }

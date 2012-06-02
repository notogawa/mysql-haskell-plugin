module FFIInterpreter where

import qualified Language.Haskell.Interpreter as I
import Foreign.C.String (CString, peekCString, newCString)

foreign export ccall eval :: CString -> IO CString
eval :: CString -> IO CString
eval expr = peekCString expr >>=
            I.runInterpreter . (I.setImports ["Prelude"] >> ) . I.eval >>=
            newCString . either show id

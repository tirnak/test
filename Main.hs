module Main where

import Graphics.UI.Gtk
import System.Process
import System.Process.Internals
import Control.Exception
import System.IO
import Data.Maybe

quote :: String -> String
quote s = "\"" ++ s ++ "\""

togglePlaying :: ProcessHandle -> ToggleButton -> IO ()
togglePlaying ph b = do
  state <- toggleButtonGetActive b
  if state
    then do
        createProcess (shell $ "pkill -SIGSTOP mpg321")
        return ()
    else do
        createProcess (shell $ "pkill -SIGCONT mpg321")
        return ()

main :: IO ()
main = do
    initGUI
    r <- createProcess (proc "ls" [])
    window <- windowNew
    vbox <- vBoxNew False 0
    set window [windowTitle := "My Player",
                 windowDefaultWidth := 500, windowDefaultHeight := 800]
    table <- tableNew 8 1 True
    containerAdd window table

    fch <- fileChooserWidgetNew FileChooserActionOpen
    tableAttachDefaults table fch 0 1 0 5
    label <- labelNew $ Just "Some information about a file being played"
    tableAttachDefaults table label 0 1 6 7
    button <- toggleButtonNewWithLabel "Play/Pause"
    tableAttachDefaults table button 0 1 7 8

    onFileActivated fch $ do
        file <- fileChooserGetFilename fch
        labelSetText label $ fromMaybe "empty" file
        case file of
            Just fpath -> do
                (_, Just hout, _, ph) <- createProcess (shell $ "/usr/bin/mpg321 " ++ quote fpath){std_out = CreatePipe }
                onToggled button (togglePlaying ph button)
                return ()
            Nothing -> putStrLn "Nothing"
    widgetShowAll window
    onDestroy window mainQuit
    mainGUI
